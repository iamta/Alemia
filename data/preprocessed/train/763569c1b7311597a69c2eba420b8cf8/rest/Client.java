package ro.mta.library_project.Communication;
import java.math.BigInteger;
import java.net.*;
import java.io.*;
import java.security.SecureRandom;
import java.util.HashMap;
import java.util.Properties;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.json.JSONObject;


public class Client
{
    // initialize socket and input output streams
    private static Client instance=null;
    private static Socket serverSocket = null;
    private static  DataInputStream myInput = null;
    private static DataOutputStream myOut = null;
    private static BigInteger key;
    // constructor to put ip address and port
    private Client(String address, int port)
    {
        // establish a connection
        try
        {
            String income="";
            serverSocket = new Socket(address, port);
            System.out.println("Connected");
            myInput  = new DataInputStream(serverSocket.getInputStream());
            myOut = new DataOutputStream(serverSocket.getOutputStream());
            SecureRandom secured= new SecureRandom();
            int L=secured.nextInt();
            income=myInput.readUTF();
            ObjectMapper mapper = new ObjectMapper();
            HashMap joIn=mapper.readValue(income, new TypeReference<HashMap<String, BigInteger>>(){});
            BigInteger G= (BigInteger) joIn.get("generator");
            BigInteger P= (BigInteger) joIn.get("modulus");
            BigInteger serverResult=(BigInteger)joIn.get("result");
            BigInteger myResult=G.modPow(new BigInteger(String.valueOf(L)),P);
            this.key=serverResult.modPow(new BigInteger(String.valueOf(L)),P);
            JSONObject jo = new JSONObject();
            jo.put("result", myResult);
            myOut.writeUTF(jo.toString());
        }
        catch (JsonProcessingException e) {
            e.printStackTrace();
        }
        catch(UnknownHostException u)
        {
            System.out.println(u);
        }
        catch(IOException i)
        {
            System.out.println(i);
        }
        catch (Exception e){
            System.out.println("Something went wrong in DBController.");
        }


    }

    public static Client getInstance(){
        if(instance==null){
            instance=new Client("127.0.0.1", 9000);
        }

        return instance;
    }

    public void sendData(String data)  {
        try {
            myOut.writeUTF(data);
        }
        catch(IOException i)
        {
            System.out.println(i);
        }
    }

    public String recvData()  {
        String income="";
        try {
            income=myInput.readUTF();
        }
        catch(IOException i)
        {
            System.out.println(i);
        }
        return income;
    }

}