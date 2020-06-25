package com.vk.dwzkf.finder;

import com.vk.dwzkf.exception.BadDataException;
import com.vk.dwzkf.helper.Helper;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

public class PathFinder {
    private Integer[][] map;
    private ArrayList<String> cities;
    private ArrayList<String> pointCities;
    private Integer[][] resultMap;
    private Integer[][] paths;
    private Result[][] results;
    private ArrayList<String> resultPath;
    private String firstCity;
    private ArrayList<String> way;

    public class Result {
        private ArrayList<String> usedCities = new ArrayList<>();
        private int value = 0;

        public boolean contains(Object o) {
            return usedCities.contains(o);
        }

        public void add(String s) {
            usedCities.add(s);
        }

        public void setValue(int v) {
            value = v;
        }

        public int getValue() {
            return value;
        }

        public ArrayList<String> getUsedCities() {
            return usedCities;
        }
    }

    private int getDistance(String cityA, String cityB) {
        int i = cities.indexOf(cityA);
        int j = cities.indexOf(cityB);
        return resultMap[i][j];
    }

    private Result getMin(String cityFrom, ArrayList<String> points, ArrayList<String> usedCities) {
        int index = this.cities.indexOf(cityFrom);
        int min = Helper.INFINITY;
        int pos = -1;
        int iterator = 0;
        for (int i = 0; i<this.cities.size(); i++) {
            if (!points.contains(cities.get(i))) continue;
            if (usedCities.contains(points.get(iterator))) {
                iterator++;
                continue;
            }
            int currentCity = cities.indexOf(points.get(iterator));
            if (resultMap[index][currentCity] < min) {
                min = resultMap[index][currentCity];
                pos = currentCity;
            }
            iterator++;
        }
        Result r = new Result();
        r.add(cities.get(pos));
        r.setValue(min);
        return r;
    }

    public PathFinder(Integer[][] map, ArrayList<String> cities){
        this.map = map;
        this.cities = cities;
        resultMap = new Integer[map.length][map.length];
        paths = new Integer[map.length][map.length];
        for (int i = 0; i<map.length; i++) {
            for (int j = 0; j<map.length; j++) {
                resultMap[i][j] = map[i][j];
                if (map[i][j] != Helper.INFINITY){
                    paths[i][j] = i;
                }
                else {
                    paths[i][j] = -1;
                }
            }
        }
    }

    public void makeNoise(String firstCity, ArrayList<String> pointCities) throws BadDataException {
        if (firstCity==null) throw new BadDataException("Error! First city is null.");
        if (pointCities==null || pointCities.size()==0) {
            throw new BadDataException("Error! Point cities is null or empty.");
        }
        this.firstCity = firstCity;
        this.pointCities = pointCities;
        createResultMap();
        findPath(pointCities);
        createResultPath();
        createPathOfEverything();
        PROFIT();
    }

    //floyd algorithm
    private void createResultMap(){
        int size = map.length;
        for (int k = 0; k<size; k++) {
            for (int i = 0; i<size; i++) {
                for (int j = 0; j<size; j++) {
                    if (resultMap[i][k] + resultMap[k][j] < resultMap[i][j]) {
                        resultMap[i][j] = resultMap[i][k] + resultMap[k][j];
                        paths[i][j] = paths[k][j];
                    }
                }
            }
        }
    }

    private void findPath(ArrayList<String> cities) {
        Result[][] result = new Result[cities.size()][cities.size()];
        for (int i = 0; i<cities.size(); i++) {
            for (int j = 0; j<cities.size(); j++) {
                result[i][j] = new Result();
            }
        }
        for (int i = 0; i<cities.size(); i++) {
            result[0][i].setValue(getDistance(firstCity, cities.get(i)));
            result[0][i].add(cities.get(i));
        }

        for (int i = 1; i<cities.size(); i++) {
            for (int j = 0; j<cities.size(); j++) {
                result[i][j].value = result[i-1][j].value;
                result[i][j].usedCities.addAll(result[i-1][j].usedCities);
                Result r = getMin(cities.get(j), cities, result[i][j].usedCities);
                result[i][j].usedCities.addAll(r.usedCities);
                result[i][j].value += r.value;
            }
        }
        this.results = result;
    }

    private void createResultPath(){
        int i = results.length-1;
        int min = 0;
        for (int j = 0; j<results[i].length; j++) {
            if (results[i][min].getValue() > results[i][j].getValue()) {
                min = j;
            }
        }
        ArrayList<String> result = new ArrayList<>();
        ArrayList<String> usedCitiesList = results[i][min].usedCities;
        for (i = 0; i<usedCitiesList.size(); i++) {
            result.add(usedCitiesList.get(i));
        }
        this.resultPath = result;
    }

    private void createPathOfEverything(){
        ArrayList<String> way = new ArrayList<String>();
        ArrayList<String> newWay;
        way.add(firstCity);
        resultPath.add(0, firstCity);
        for (int i = 0; i<resultPath.size()-1; i++) {
            int checker = 0;
            newWay = getWay(resultPath.get(i), resultPath.get(i+1));
            for (int k = newWay.size()-1; k>=0; k--) {
                way.add(newWay.get(k));
            }
            for (int k = 0; k<pointCities.size(); k++) {
                if (way.contains(pointCities.get(k))) {
                    checker++;
                }
            }
            if (checker==pointCities.size()) {
                break;
            }
        }
        this.way = way;
    }

    private ArrayList<String> getWay(String cityFrom, String cityTo) {
        ArrayList<String> way = new ArrayList<String>();
        if (cityFrom.equals(cityTo)) return way;
        int i = cities.indexOf(cityFrom);
        int j = cities.indexOf(cityTo);
        while (true) {
            way.add(cities.get(j));
            if (paths[i][j] == i) break;
            j = paths[i][j];
        }
        return way;
    }

    private void PROFIT(){

    }

    public ArrayList<String> getWay(){
        ArrayList<String> points = new ArrayList<>(this.pointCities);
        points.add(0,firstCity);
        ArrayList<String> result = new ArrayList<>();
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i<way.size(); i++) {
            sb.delete(0,sb.length());
            sb.append(way.get(i));
            if (points.contains(way.get(i))) {
                sb.append("(P)");
                points.remove(way.get(i));
            }
            else {
                sb.append("(T)");
            }
            sb.append("--->");
            result.add(sb.toString());
        }
        sb.delete(0,sb.length());
        int i = results.length-1;
        int min = 0;
        for (int j = 0; j<results[i].length; j++) {
            if (results[i][min].getValue() > results[i][j].getValue()) {
                min = j;
            }
        }
        sb.append("END (Length = ");
        sb.append(results[i][min].getValue());
        sb.append(")");
        result.add(sb.toString());
        return result;
    }

    public Integer[][] getPaths() {
        return paths;
    }

    public Integer[][] getResultMap() {
        return resultMap;
    }

    public Result[][] getResults(){
        return results;
    }
}
