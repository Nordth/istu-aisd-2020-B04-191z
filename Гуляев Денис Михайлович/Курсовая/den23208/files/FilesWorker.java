package den23208.files;


import den23208.obj.Place;
import den23208.obj.Word;
import den23208.text.TextHelper;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.ArrayList;

public class FilesWorker {
    public FilesWorker(){

    }

    public ArrayList<Path> loadFilesFromPath(String path){
        try {
            ArrayList<Path> files = new ArrayList<>();
            Files.walkFileTree(Paths.get(path), new SimpleFileVisitor<>() {
                @Override
                public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) throws IOException {
                    if (Files.isRegularFile(file)) {
                        if (file.getFileName().toString().endsWith(".txt")) {
                            files.add(file);
                        }
                    }
                    return FileVisitResult.CONTINUE;
                }
            });
            return files;
        }
        catch (Exception e) {
            System.err.println("Can't load files from path: "+path);
            return null;
        }
    }

    public ArrayList<Word> getAllWords(Path path) throws IOException {
        ArrayList<String> lines = new ArrayList<>(Files.readAllLines(path, Charset.forName("UTF-8")));
        ArrayList<Word> words = new ArrayList<>();
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i<lines.size(); i++) {
            String l = lines.get(i);
            sb.delete(0, sb.length());
            char[] array = l.toCharArray();
            for (int k = 0; k<array.length; k++) {
                char c = array[k];
                if (TextHelper.isNotSplitter(c)) {
                    sb.append(c);
                }
                else {
                    if (sb.length()>0) {
                        String newWord = sb.toString().toLowerCase();
                        sb.delete(0, sb.length());
                        Place place = new Place();
                        place.addRows(i);
                        place.setFile(path.toString());
                        Word word = new Word(newWord);
                        word.addPlace(place);
                        words.add(word);
                    }
                }
            }
            if (sb.length()>0) {
                String newWord = sb.toString().toLowerCase();
                Place place = new Place();
                place.addRows(i);
                place.setFile(path.toString());
                Word word = new Word(newWord);
                word.addPlace(place);
                words.add(word);
            }
        }
        return words;
    }
}
