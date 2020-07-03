package com.vk.dwzkf.app;


import com.vk.dwzkf.data.DataWorker;
import com.vk.dwzkf.ui.UserInterface;

public class Application {
    UserInterface ui = new UserInterface();
    DataWorker dw = new DataWorker();

    public static void main(String[] args) {
        Application app = new Application();
        app.run();
    }

    public void run(){
        ui.setDataWorker(dw);
        ui.start();
    }
}
