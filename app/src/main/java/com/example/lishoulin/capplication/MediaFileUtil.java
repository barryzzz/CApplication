package com.example.lishoulin.capplication;

import java.util.concurrent.LinkedBlockingQueue;

/**
 * @author lishoulin
 * @version 1.0
 * @date 2018/7/30
 */
public class MediaFileUtil {


    public void test() {
    }


    public static void main(String arhs[]) {
        System.out.println(-5 >> 1);
    }


    class CustomQueue extends Thread {

        private LinkedBlockingQueue<byte[]> mQueue;

        public CustomQueue(LinkedBlockingQueue<byte[]> queue) {
            mQueue = queue;
            start();
        }


        @Override
        public void run() {
            while (true) {
                byte[] data = null;
                try {
                    data = mQueue.take();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    break;
                }
            }
        }
    }
}
