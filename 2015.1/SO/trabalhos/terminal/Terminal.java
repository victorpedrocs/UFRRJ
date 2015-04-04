import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Terminal {
	
	public static void main(String[] args) {
		Terminal terminal = new Terminal();
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String output = new String("");
		String command = new String("");
		
		System.out.println("Simulador de terminal");
		
		while (!command.equals("exit")) {
			System.out.print("$ ");
			try {
				command = br.readLine();
				output = terminal.executeCommand(command);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			System.out.println(output);
		}
		
		
	}

	private String executeCommand(String command) {
		StringBuilder output = new StringBuilder();
		
		try {
			Process process = Runtime.getRuntime().exec(command);
			process.waitFor();
			BufferedReader br = new BufferedReader(new InputStreamReader(process.getInputStream()));
			
			String linha = "";
			
			while( (linha = br.readLine()) != null) {
				output.append(linha).append("\n");
			}
		} catch (IOException e) {
			System.err.println("Command not found");
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		return output.toString();
	}
}
