package com.jtrzyna.BalanSyner;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

/**
 * Created by Kuba on 2015-07-14.
 */
public class BtManager {

    private int myID = 0;
    //common defines

    public final static byte _CR = 0x0D;
    public final static byte _LF = 0x0A;

    public final static int SUCCESS_CONNECT = 6;
    public final static int MESSAGE_READ = 7;
    public final static int ERROR = -1;
    public final static int TERMINATE = -2;
    private final static int _DUMMY = 0;


    public static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    public ConnectThread connectThread;
    public ConnectedThread connectedThread;
    public BluetoothDevice device;

    //external handler to communicate with MainActivity
    private final Handler mainHandler;

    //internal handler to establish bt connection
    private final Handler btHandler = new Handler(){
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            switch(msg.what){
                case SUCCESS_CONNECT:
                    Log.d("btHandler", "SUCCESS_CONNECT");
                    connectedThread = new ConnectedThread((BluetoothSocket)msg.obj);
                    connectedThread.start();
                    break;
                /*case MESSAGE_READ: //unused: msgs are send directly to MainActivity
                    //byte[] readBuf = (byte[]) msg.obj;
                    //String readMessage = new String(readBuf, 0, msg.arg1);
                    //Log.d("incomingMsg", readMessage);
                    break;*/
                case ERROR:
                    Log.d("btHandler", "ERROR");
                    break;
            }
        }
    };

    public BtManager(Handler mHandler){
        mainHandler = mHandler;
        myID =_DUMMY;
    }

    public BtManager(Handler mHandler, int ID){
        mainHandler = mHandler;
        myID = ID;
    }

    public void connect(BluetoothDevice mDevice){
        device = mDevice;
        connectThread = new ConnectThread(device);
        connectThread.start();
    }

    public void disconnect(){
        Log.d("connectThread", "disconnect");
        try{
            if(connectThread.mmSocket.isConnected()){
                Log.d("connectThread", "isConnected, cancel");
                connectThread.cancel();
            }
        } catch (Exception e){
            //e.printStackTrace();
        }
    }

    public void sendMessage(String msg){
        try {
            connectedThread.write(msg.getBytes());
        } catch(Exception e){
            e.printStackTrace();
        }
    }

    public void sendMessage(byte msg){
        try {
            connectedThread.write(msg);
        } catch(Exception e){
            e.printStackTrace();
        }
    }

    public void sendMessage(int[] msg){
        try {
            byte tmp[] = new byte[msg.length];
            for (int i = 0; i < msg.length; i++) {
                tmp[i] = (byte) msg[i];
            }
            connectedThread.write(tmp);
        } catch (Exception e){
            e.printStackTrace();
        }
    }

    public class ConnectThread extends Thread {
        private final BluetoothSocket mmSocket;
        private final BluetoothDevice mmDevice;

        public ConnectThread(BluetoothDevice device) {
            // Use a temporary object that is later assigned to mmSocket,
            // because mmSocket is final
            BluetoothSocket tmp = null;
            mmDevice = device;

            // Get a BluetoothSocket to connect with the given BluetoothDevice
            try {
                // MY_UUID is the app's UUID string, also used by the server code
                tmp = device.createRfcommSocketToServiceRecord(MY_UUID);
            } catch (IOException e) { }
            mmSocket = tmp;
        }

        public void run() {
            // Cancel discovery because it will slow down the connection
            //mBluetoothAdapter.cancelDiscovery();

            Log.d("ConnectThread", "run "+mmDevice.getName());
            try {
                // Connect the device through the socket. This will block
                // until it succeeds or throws an exception
                mmSocket.connect();
            } catch (IOException connectException) {
                // Unable to connect; close the socket and get out
                try {
                    mmSocket.close();
                } catch (IOException closeException) {
                    Log.d("closeException", closeException.getMessage());
                }
                Log.d("connectException "+ mmDevice.getName(), connectException.getMessage());
                mainHandler.obtainMessage(ERROR).sendToTarget();
                return;
            }
            btHandler.obtainMessage(SUCCESS_CONNECT, mmSocket).sendToTarget();

        }

        /** Will cancel an in-progress connection, and close the socket */
        public void cancel() {
            try {
                mmSocket.close();
            } catch (IOException e) {
                Log.d("connect cancel", e.getMessage());
            }
        }
    }

    private class ConnectedThread extends Thread {
        private final BluetoothSocket mmSocket;
        private final InputStream mmInStream;
        private final OutputStream mmOutStream;

        public ConnectedThread(BluetoothSocket socket) {
            mmSocket = socket;
            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            // Get the input and output streams, using temp objects because
            // member streams are final
            try {
                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();
                Log.d("connected", "success");

            } catch (IOException e) {
                mainHandler.obtainMessage(ERROR).sendToTarget();
                Log.d("connected socket", e.getMessage());
            }

            mmInStream = tmpIn;
            mmOutStream = tmpOut;
        }

        public void run() {
            byte[] buffer;  // buffer store for the stream
            int bytes; // bytes returned from read()
            mainHandler.obtainMessage(SUCCESS_CONNECT, myID, _DUMMY).sendToTarget();

            // Keep listening to the InputStream until an exception occurs
            while (true) {
                try {
                    buffer = new byte[1024];
                    // Read from the InputStream
                    bytes = mmInStream.read(buffer);
                    // Send the obtained bytes to the UI activity
                    mainHandler.obtainMessage(MESSAGE_READ, myID, bytes, buffer).sendToTarget();
                    try{
                        sleep(200);
                    } catch(InterruptedException e){
                        e.printStackTrace();
                    }
                } catch (IOException e) {
                    Log.d("readException", e.getMessage());
                    break;
                }
            }
        }

        /* Call this from the main activity to send data to the remote device */
        public void write(byte[] bytes) {
            try {
                mmOutStream.write(bytes);
                String str = new String(bytes);
                //Log.d("writeStream[]", str);
            } catch (IOException e) {
                Log.d("writeStream[]Error", e.getMessage());
            }
        }

        public void write(byte bytes) {
            try {
                mmOutStream.write(bytes);
                //String str = new String((new byte[] {bytes}));
                //Log.d("writeStream", str );
            } catch (IOException e) {
                Log.d("writeStreamError", e.getMessage());
            }
        }

        /* Call this from the main activity to shutdown the connection */
        public void cancel() {
            try {
                mmSocket.close();
            } catch (IOException e) {
                Log.d("connected cancel", e.getMessage());}
        }
    }

}
