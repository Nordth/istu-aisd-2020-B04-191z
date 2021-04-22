package com.company;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class Indexing {

    static  IndexFile indexFile;

    public void index() throws IOException {

       BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Введите директорию для сканирования:");
        //File folder = new File("C:\\Users\\airat\\Desktop\\Новая папка");
        String filename = reader.readLine();
        Path path = Paths.get(filename);
        if (Files.notExists(path)){
            System.err.println("Ошибка! Такой дериктории нет, введите команду!");
            return;
        }
        File folder =new File(String.valueOf(path));
        File[] listOfFiles = folder.listFiles();
        if (listOfFiles.length == 0) {
            System.out.println("Нет данных для сканирования");
        } else {
            System.out.println("Найдено " + listOfFiles.length + " файлов для сканирования");
            System.out.println("Введите слово для начала сканирования");
            String word = null;
            try {
                word = reader.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            String wordString = word;

            Map<String,Set<Word>> map = new HashMap<>();
            LinkedHashSet<Word> linkedHashSet = new LinkedHashSet<>();
            for (File file : listOfFiles) {
                if (file.isFile()) {
                    List<Word> listAllWord = run(folder , file.getName());
                    Set<Word> setByTheFoundWord = findWord(listAllWord, wordString);
                    linkedHashSet.addAll(setByTheFoundWord);
                }
            }
            map.put(word,linkedHashSet);
            indexFile = new IndexFile();
            indexFile.setWord(map);
            show();
        }
    }

    public static void show(){
        if (indexFile==null){
            System.out.println("Пустой");
        }else {
            Map<String,Set<Word>> map = indexFile.getWord();
            for (Map.Entry<String,Set<Word>> pair : map.entrySet()){
                System.out.println("Слово:" + pair.getKey());
                System.out.println("Встретилось:" + pair.getValue());
            }
        }
    }

    public static List<Word> run(File file,String fileName) {
        String fullFileName = file+ "\\"+ fileName;
        List<Word> allLineWords =new ArrayList<>();
        int lineInt = 1;
        try {
            BufferedReader reader = new BufferedReader(new FileReader(fullFileName));
            String lineString;
            String result = "";

            while ((lineString = reader.readLine()) != null) {
                result = lineString;
                Word words = new Word();
                words.setLine(lineInt);
                lineInt++;
                words.setLineWords(result);
                words.setFileName(fileName);
                allLineWords.add(words);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        lineInt = 1;
        return allLineWords;
    }

    private static LinkedHashSet<Word> findWord(List<Word> allLineWords, String word) {
        LinkedHashSet<Word> wordList =new LinkedHashSet<>();
        for (int i = 0; i < allLineWords.size(); i++) {

            String lineWords = allLineWords.get(i).getLineWords();
            List<String> oneWord = Arrays.asList(lineWords.split(" "));
            for (int j = 0; j < oneWord.size(); j++) {

                if (oneWord.get(j).equals(word)){
                    Word w = new Word();
                    w.setLineWords(allLineWords.get(i).getLineWords());
                    w.setLine(allLineWords.get(i).getLine());
                    w.setFileName(allLineWords.get(i).getFileName());
                    wordList.add(w);
                }
            }
        }
        if (wordList.size() == 0){
            System.out.println("Не нашлось совпадений");
        }
        return wordList;
    }
}
