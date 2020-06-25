package com.vk.dwzkf.helper;

import java.util.List;

public class Helper {
    public static final int INFINITY = 999999;
    public static <T> void printArray(T[][] array) {
        for (int i = 0; i<array.length; i++) {
            for (int j = 0; j<array[i].length; j++) {
                System.out.printf("%6s ",array[i][j]);
            }
            System.out.println();
        }
    }

    public static <T> void printArray(T[] array) {
        for (int i = 0; i<array.length; i++) {
                System.out.printf("%2s ",array[i]);
        }
        System.out.println();
    }

    public static <T> void printList(List<T> list){
        for (int i = 0; i<list.size(); i++) {
            System.out.print(list.get(i)+" ");
        }
        System.out.println();
    }
}
