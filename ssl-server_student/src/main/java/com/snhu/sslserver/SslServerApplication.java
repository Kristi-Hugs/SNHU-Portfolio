package com.snhu.sslserver;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import org.apache.tomcat.util.buf.HexUtils;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class SslServerApplication {

    public static void main(String[] args) {
        SpringApplication.run(SslServerApplication.class, args);
    }

    @RequestMapping("/hash")
    public String myHash() throws NoSuchAlgorithmException {

        String data = "Kristi Huggins";

        MessageDigest msgDigest = MessageDigest.getInstance("SHA-256");
        byte[] byteArr = msgDigest.digest(data.getBytes());

        String checksum = HexUtils.toHexString(byteArr);

        MessageDigest verifyDigest = MessageDigest.getInstance("SHA-256");
        byte[] verifyArr = verifyDigest.digest(data.getBytes());

        String verifyChecksum = HexUtils.toHexString(verifyArr);

        boolean same = checksum.equals(verifyChecksum);

        return "data: " + data
                + "<br><br>checksum: " + checksum
                + "<br><br>verification checksum: " + verifyChecksum
                + "<br><br>Same? " + same;
    }
}
   
   


        

     
       