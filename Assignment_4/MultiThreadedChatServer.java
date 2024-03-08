import java.io.*;
import java.net.*;
import java.util.*;

public class MultiThreadedChatServer {
    private static final int PORT = 12345;
    private static List<ClientHandler> clients = new ArrayList<>();

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Server started. Listening on port " + PORT);

            while (true) {
                Socket clientSocket = serverSocket.accept();
                System.out.println("New client connected: " + clientSocket);

                ClientHandler clientHandler = new ClientHandler(clientSocket);
                clients.add(clientHandler);
                clientHandler.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    static class ClientHandler extends Thread {
        private final Socket clientSocket;
        private PrintWriter out;
        private BufferedReader in;

        public ClientHandler(Socket socket) {
            this.clientSocket = socket;
        }

        public void run() {
            try {
                out = new PrintWriter(clientSocket.getOutputStream(), true);
                in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

                String username = in.readLine();
                System.out.println(username + " joined the chat.");

                String inputLine;
                while ((inputLine = in.readLine()) != null) {
                    if ("exit".equalsIgnoreCase(inputLine)) {
                        break;
                    }
                    System.out.println(username + ": " + inputLine);
                    for (ClientHandler client : clients) {
                        if (client != this) {
                            client.sendMessage(username + ": " + inputLine);
                        }
                    }
                }

                clients.remove(this);
                System.out.println(username + " left the chat.");
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        public void sendMessage(String message) {
            out.println(message);
        }
    }
}
