package com.vk.dwzkf.ui;

import com.vk.dwzkf.data.DataWorker;
import com.vk.dwzkf.exception.BadDataException;
import com.vk.dwzkf.finder.PathFinder;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class UserInterface {
    DataWorker dw;
    boolean isMapLoaded = false;

    public void setDataWorker(DataWorker dw) {
        this.dw = dw;
    }


    public void start(){
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            try {
                showTip();
                String s = r.readLine();
                int act = Integer.valueOf(s);
                if (act == 1) {
                    try {
                        System.out.println("Enter path (or nothing if use default): ");
                        String path = r.readLine();
                        if (path == null || path.isEmpty()) {
                            dw.loadMap();
                        }
                        else {
                            dw.loadMap(path);
                        }
                        isMapLoaded = true;
                        System.out.println("Map loaded.");
                    }
                    catch (Exception e) {
                        isMapLoaded = false;
                    }
                }
                else if (act == 2) {
                    if (!isMapLoaded) {
                        throw new BadDataException("No MAP loaded.");
                    }
                    System.out.print("Print path (Example: A B C..): ");
                    String[] cities = r.readLine().split(" ");
                    if (!checkCities(cities)) {
                        throw new BadDataException("Wrong cities.");
                    }
                    ArrayList<String> points = new ArrayList<String>();
                    for (int i = 1; i<cities.length; i++) {
                        points.add(cities[i]);
                    }
                    PathFinder p = new PathFinder(dw.getCitiesMap(), dw.getCities());
                    p.makeNoise(cities[0], points);
                    System.out.println("T - transit city. P - point city.");
                    for (String str : p.getWay()) {
                        System.out.print(str);
                    }
                    System.out.println();
                }
                else if (act == 3) {
                    System.out.println("Exit.");
                    break;
                }
            }
            catch (Exception e) {

            }
        }
    }

    private boolean checkCities(String[] cities) {
        int checker = 0;
        for (int i = 0; i<cities.length; i++) {
            if (dw.getCities().contains(cities[i])) checker++;
        }
        return checker == cities.length;
    }

    private void showTip() {
        System.out.println("1 - Load map.");
        System.out.println("2 - Find path.");
        System.out.println("3 - Exit.");
    }
}
