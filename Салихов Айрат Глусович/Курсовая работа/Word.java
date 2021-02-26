package com.company;

import java.util.Objects;

public class Word {

    int line;
    String lineWords;
    String fileName;

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }


    public String getLineWords() {
        return lineWords;
    }

    public void setLineWords(String lineWords) {
        this.lineWords = lineWords;
    }

    public int getLine() {
        return line;
    }

    public void setLine(int line) {
        this.line = line;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Word word = (Word) o;
        return getLine() == word.getLine() && Objects.equals(getLineWords(), word.getLineWords()) && Objects.equals(getFileName(), word.getFileName());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getLine(), getLineWords(), getFileName());
    }

    @Override
    public String toString() {
        return "\n" +
                "\nНомер строки: " + line +
                ", \nВ строке: " + lineWords + '\'' +
                ", \nВ файле: " + fileName + '\'' +
                "\n";
    }
}
