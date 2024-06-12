package org.example.factory;

import org.example.commands.Command;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.InputStream;
import java.util.HashMap;
import java.util.Properties;


public class Factory {
    private static final Logger logger = LogManager.getLogger(Factory.class);
    public static Factory getInstance() {
        logger.info("Getting instance of Factory");
        return f;
    }
    public void initCommandNames() {
        InputStream in = Factory.class.getClassLoader().getResourceAsStream("operands.properties");
        Properties properties = new Properties();

        try {
            logger.info("Reading properties from file");
            properties.load(in);
        } catch (Exception ex) {
            logger.error("Properties file not found");
        }

        for(String key : properties.stringPropertyNames()) {
            commandNames.put(key, properties.getProperty(key));
        }
    }
    public Command createCommand(String commandName) {
        if(!commandNames.containsKey(commandName)) {
            logger.error(commandName + " is not registered");
            throw new RuntimeException(commandName + " is not registered");
        }

        Command command = null;
        String commandClassName = commandNames.get(commandName);
        try {
            logger.info("Creating command " + commandClassName);
            command = (Command) Class.forName("org.example.commands." + commandClassName).getDeclaredConstructor().newInstance();
        } catch(Exception ex) {
            logger.error(commandName + " creation failed");
            System.out.println(ex.getMessage());
        }
        return command;
    }
    public boolean isRegistered(String key) {
        return commandNames.containsKey(key);
    }
    private Factory() {
        initCommandNames();
    }
    private static final Factory f = new Factory();
    private final HashMap<String, String> commandNames = new HashMap<>();
}


