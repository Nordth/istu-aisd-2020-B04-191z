package den23208.text;

public class TextHelper {
    private static char[] splitters = {' ', '.',';','>','<','\\', '/', '.', '?', '!', '(', ')', '\'', ','};
    private static int[] arr;


    static {
        int max = 0;
        for (int i = 0; i<splitters.length; i++) {
            if ((int) splitters[i] > max) {
                max = (int) splitters[i];
            }
        }
        arr = new int[max+1];
        for (int i = 0; i<arr.length; i++) {
            arr[i] = 0;
        }
        for (char c : splitters) {
            arr[(int) c] = 1;
        }
    }

    public static void setSplitters(char[] splitters){
        TextHelper.splitters = splitters;
    }

    public static boolean isNotSplitter(char a) {
        if ((int) a >= arr.length) return true;
        return (arr[(int) a] == 0);
    }
}
