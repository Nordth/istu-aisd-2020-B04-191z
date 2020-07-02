package den23208.obj;

import java.io.Serializable;
import java.util.ArrayList;

public class Word implements Serializable {
    public String word;
    public ArrayList<Place> places = new ArrayList<>();

    public Word(String word){
        this.word = word;
    }

    public void addPlace(Place place){
        places.add(place);
    }

    public void updatePlaces(Word w){
        ArrayList<Place> placeList = w.getPlaces();
        for (int i = 0; i<placeList.size(); i++) {
            if (places.contains(placeList.get(i))) {
                int index = places.indexOf(placeList.get(i));
                Place p = places.get(index);
                p.updateRows(placeList.get(i).getRows());
            }
            else {
                places.add(placeList.get(i));
            }
        }
    }

    public void removePlace(Place place) {
        places.remove(place);
    }

    public int getPlacesSize(){
        return places.size();
    }

    public ArrayList<Place> getPlaces(){
        return new ArrayList<>(places);
    }

    public void setWord(String word){
        this.word = word;
    }

    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Founded Word: ");
        sb.append(word);
        sb.append("\n");
        return sb.toString();
    }

    @Override
    public boolean equals(Object o){
        if (o==null) return false;
        if (!(o instanceof Word)) return false;
        Word w = (Word) o;
        return w.word.equalsIgnoreCase(this.word);
    }
}
