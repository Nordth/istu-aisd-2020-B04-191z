package com.vk.dwzkf.data;

import com.vk.dwzkf.exception.BadDataException;
import com.vk.dwzkf.helper.Helper;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;

public class DataWorker {
    private String path = "data\\data.txt";
    private BufferedReader reader;
    private ArrayList<String> data = new ArrayList<String>();
    private ArrayList<String> cities = new ArrayList<String>();
    private Integer[][] map;

    public boolean loadMap() throws FileNotFoundException, BadDataException {
        return loadMap(path);
    }

    public boolean loadMap(String path) throws FileNotFoundException, BadDataException {
        loadData(path);
        if (data.size()==0) throw new BadDataException("Bad data.");
        String[] _cities = data.get(0).split("[ ,]");
        if (_cities.length <=0 ) {
            throw new BadDataException("Can't load data: No cities.");
        }
        if (data.size()-1 != _cities.length) {
            throw new BadDataException("Can't load data: Bad size of map.");
        }
        cities.clear();
        for (int i = 0; i < _cities.length; i++) {
            if (cities.contains(_cities[i])) {
                throw new BadDataException("Can't load data: 2 equals cities");
            }
            cities.add(_cities[i]);
        }

        map = new Integer[cities.size()][cities.size()];
        for (int i = 1; i<data.size(); i++) {
            String[] s = data.get(i).split(" ");
            if (s.length != data.size()-1) throw new BadDataException("Can't load data: Bad rows.");
            for (int j = 0; j < s.length; j++) {
                if ("-".equals(s[j])) {
                    map[i-1][j] = 0;
                }
                else if ("?".equals(s[j])) {
                    map[i-1][j] = Helper.INFINITY;
                }
                else {
                    try {
                        int n = Integer.valueOf(s[j]);
                        map[i-1][j] = n;
                    }
                    catch (NumberFormatException e) {
                        throw new BadDataException("Can't load data: Bad number in map.");
                    }
                }
            }
        }
        return true;
    }

    private void loadData(String path) throws FileNotFoundException {
        reader = new BufferedReader(new InputStreamReader(new FileInputStream(new File(path))));
        String s;
        try {
            data.clear();
            while ((s = reader.readLine()) != null) {
                if (s.charAt(0) !=';') {
                    data.add(s);
                }
            }
            reader.close();
        }
        catch (java.io.IOException e) {

        }
    }

    public Integer[][] getCitiesMap(){
        return map;
    }

    public ArrayList<String> getCities(){
        ArrayList<String> result = new ArrayList<String>();
        result.addAll(cities);
        return result;
    }
}
