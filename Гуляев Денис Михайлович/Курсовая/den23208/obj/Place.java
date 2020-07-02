package den23208.obj;

import java.io.Serializable;
import java.nio.file.Path;
import java.util.ArrayList;

public class Place implements Serializable {
    public String file;
    public ArrayList<Integer> rows = new ArrayList<>();

    public void setFile(String file) {
        this.file = file;
    }

    public void addRows(int row){
        rows.add(row);
    }

    public void updateRows(ArrayList<Integer> rowsList) {
        for (int i = 0; i<rowsList.size(); i++) {
            if (!rows.contains(rowsList.get(i))) {
                rows.add(rowsList.get(i));
            }
        }
    }

    public ArrayList<Integer> getRows(){
        return new ArrayList<>(rows);
    }

    public String getFile(){
        return file;
    }

    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\tFile: ");
        sb.append(file);
        sb.append("\n");
        if (rows.size()>0) {
            sb.append("\t\tRows: ");
            for (int i = 0; i<rows.size() - 1; i++) {
                sb.append(rows.get(i));
                sb.append(", ");
            }
            sb.append(rows.get(rows.size()-1));
        }
        return sb.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) return false;
        if (!(obj instanceof Place)) return false;
        Place p = (Place) obj;
        return this.file.equalsIgnoreCase(p.file);
    }
}
