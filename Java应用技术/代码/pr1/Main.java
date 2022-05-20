import java.util.Scanner;
import java.util.TreeSet;

class ScoreInfo implements Comparable<ScoreInfo>{
	String course;
	double score;
	
	ScoreInfo() {
		
	}
	ScoreInfo(String course, double score) {
		this.course = course;
		this.score = score;
	}
	
	@Override
	public int compareTo(ScoreInfo o) {
		return this.course.compareTo(o.course);
	}
}

class StudentInfo implements Comparable<StudentInfo>{
	
	String id;
	String name;
	TreeSet<ScoreInfo> score;
	
	StudentInfo() {
		
	}
	StudentInfo(String info) {
		String[] res = info.split(", ");
		this.id = res[0];
		this.score = new TreeSet<ScoreInfo>();
		if(res.length == 3) {
			this.score.add(new ScoreInfo(res[1], Double.parseDouble(res[2])));
		} else {
			this.name = res[1];
		}
	}
	StudentInfo(String id, String name) {
		this.id = id;
		this.name = name;
		this.score = new TreeSet<ScoreInfo>();
	}
	StudentInfo(String id, ScoreInfo score) {
		this.id = id;
		this.score = new TreeSet<ScoreInfo>();
		this.score.add(score);
	}
	
	public double averageScore() {
		double sum = 0;
		for(ScoreInfo s : this.score) {
			sum += s.score;
		}
		return sum / score.size();
	}
	
	public void printFormat(TreeSet<String> courseTree) {
		System.out.format("%s, %s, ", this.id, this.name);
		for(String str : courseTree) {
			for(ScoreInfo sco : score) {
				if(sco.course.equals(str))
					System.out.print(sco.score);
			}
			System.out.print(", ");
		}
		System.out.format("%.1f", this.averageScore());
		
	}
	
	@Override
	public int compareTo(StudentInfo obj) {
		if(this != obj && this.id.equals(obj.id)) {
			if(this.name == null) {
				for(ScoreInfo s : this.score) {
					obj.score.add(s);
				}
			} else {
				obj.name = this.name;
			}
		}
		return this.id.compareTo(obj.id);	
	}
}

class Main {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		String str;
		TreeSet<StudentInfo> studentTree = new TreeSet<StudentInfo>();
		TreeSet<String> courseTree = new TreeSet<String>();
		
		while(true) {
			str = scan.nextLine();
			if(str.equals("END")) break;
			String[] res = str.split(", ");
			if(res.length == 3) {
				courseTree.add(res[1]);
				studentTree.add(new StudentInfo(res[0], new ScoreInfo(res[1], Double.parseDouble(res[2]))));
			} else {
				studentTree.add(new StudentInfo(res[0], res[1]));
			}
			
		}
		scan.close();
		
		System.out.print("student id, name, ");
		for(String s : courseTree) System.out.print(s + ", ");
		System.out.print("average");
		for(StudentInfo stu : studentTree) {
			System.out.println();
			stu.printFormat(courseTree);
		}
		
	}

}
