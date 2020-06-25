package com.vk.dwzkf.exception;

public class BadDataException extends Exception {
    public BadDataException(){

    }

    public BadDataException(String message){
        System.err.println("[ERROR]: "+message);
    }
}
