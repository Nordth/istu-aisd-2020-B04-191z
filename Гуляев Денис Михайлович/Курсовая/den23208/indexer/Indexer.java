package den23208.indexer;

import den23208.obj.Place;
import den23208.obj.Word;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;

public class Indexer {
    private ArrayList<Word> words;
    private String filename = "mydata.data";
    public Indexer() {
        try {
            ObjectInputStream ois = new ObjectInputStream(new FileInputStream(filename));
            words = (ArrayList<Word>) ois.readObject();
            System.out.println("State loaded from: "+filename);
        }
        catch (Exception e) {
            System.err.println("Can't load "+filename);
            words = new ArrayList<>();
        }
    }

    public void addWords(ArrayList<Word> words) {
        for (int i = 0; i<words.size(); i++) {
            if (this.words.contains(words.get(i))) {
                int index = this.words.indexOf(words.get(i));
                Word w = this.words.get(index);
                w.updatePlaces(words.get(i));
            }
            else this.words.add(words.get(i));
        }
    }

    public void deletePlaces(ArrayList<Path> paths) {
        Word w;
        Place place = new Place();
        for (Path p : paths) {
            int i = 0;
            place.setFile(p.toString());
            while (i<words.size()) {
                w = words.get(i);
                if (w.getPlaces().contains(place)) {
                    w.removePlace(place);
                    if (w.getPlacesSize()==0) {
                        words.remove(i);
                    }
                    else {
                        i++;
                    }
                }
                else i++;
            }
        }

    }

    public boolean checkPlaces(Word w) {
        if (words.contains(w)) {
            Word check = words.get(words.indexOf(w));
            for (Place p : check.getPlaces()) {
                if (!Files.exists(Paths.get(p.getFile()))) {
                    check.removePlace(p);
                }
            }
            if (check.getPlacesSize()==0) {
                words.remove(check);
                return false;
            }
        }
        return true;
    }

    public Word findWord(String word) {
        Word w = new Word(word);
        for (int i = 0; i<words.size(); i++) {
            if (words.get(i).equals(w)) {
                return words.get(i);
            }
        }
        return null;
    }

    public void saveState() throws IOException {
        ObjectOutputStream out = new ObjectOutputStream(Files.newOutputStream(Paths.get(filename)));
        out.writeObject(words);
        out.flush();
        out.close();
    }

    public ArrayList<Word> getWords(){
        return new ArrayList<>(words);
    }
}
