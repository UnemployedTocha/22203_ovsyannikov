import org.example.Client;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;
import java.io.IOException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class ServerTest {
    private ExecutorService executor;

    @BeforeEach
    public void setup() {
        executor = Executors.newFixedThreadPool(4);
    }

    @AfterEach
    public void tearDown() throws InterruptedException {
        executor.shutdown();
        executor.awaitTermination(5, TimeUnit.SECONDS);
    }

    @Test
    public void testMultipleClients() throws InterruptedException {
        final String[] responses = new String[4];

        for (int i = 0; i < 4; i++) {
            int clientIndex = i;
            executor.submit(() -> {
                Client client = new Client();
                try {
                    client.startConnection("127.0.0.1", 1111);
                    String response = client.sendMessage("Client " + clientIndex);
                    responses[clientIndex] = response;
                    client.sendMessage("exit");
                } catch (IOException e) {
                    e.printStackTrace();
                } finally {
                    try {
                        client.stopConnection();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            });
        }

        executor.shutdown();
        boolean finished = executor.awaitTermination(1, TimeUnit.MINUTES);

        assertEquals(true, finished);
        for (int i = 0; i < 4; i++) {
            assertEquals("Client " + i, responses[i]);
        }
    }
}