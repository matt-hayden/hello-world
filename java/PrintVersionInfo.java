import java.io.*;

public class PrintVersionInfo {
	static String format = "%s:\t%s%n";
	static String[] propnames = { "java.classpath", "java.home", "java.version", "user.home" };
	static String[] envvars = { "HOME", "TMP", "SystemRoot" };
	
	public static void main(String[] args) {
		PrintVersion();
		System.exit(0);
	}
	static void PrintVersion() {
		String v;
		PrintStream out = System.out;
		for (String p: propnames) {
			v = System.getProperty(p);
			if (v!=null) out.format(format, p, v);
		}
		for (String e: envvars) {
			v = System.getenv(e);
			if (v!=null) out.format(format, e, v);
		}
	}
}