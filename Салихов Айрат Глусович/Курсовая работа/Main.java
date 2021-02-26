package com.company;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import static com.company.Indexing.show;

public class Main {


    public static void main(String[] args) throws IOException {

        String input;
        Indexing indexing = new Indexing();
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Команды для запуска:\n" + "-find : начать поиск\n" + "-exit : выход из программы\n" + "-show : покахать IndexFile");
        label:
        while (true) {
            input = reader.readLine();

            switch (input) {
                case "-find":
                    indexing.index();
                    break;
                case "-exit":
                    break label;
                case "-show":
                    show();
                    break;
            }
        }
    }


}
