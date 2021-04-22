package com.company;


import java.util.Map;
import java.util.Set;

public class IndexFile {
    Map<String,Set<Word>> word;

    public Map<String, Set<Word>> getWord() {
        return word;
    }

    public void setWord(Map<String, Set<Word>> word) {
        this.word = word;
    }
}
