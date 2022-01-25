package ro.mta.library_project.Encoder;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.*;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;
import java.util.Base64;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;

public class Encoder {

    public Encoder() {

    }
    public String json_encode_Select(String tableName)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","Select");
        o1.put("TableName",tableName);

        return o1.toString();
    }
    public String json_encode_SelectByColumn(String tableName,String ColumnName,String Value)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","SelectByColumn");
        o1.put("TableName",tableName);
        o1.put("ColumnName",ColumnName);
        o1.put("Value",Value);

        return o1.toString();
    }
    public String json_encode_SelectByColumnV(String tableName,String ColumnName,String[] Value)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","SelectByColumnV");
        o1.put("TableName",tableName);
        o1.put("ColumnName",ColumnName);

        JSONArray jarr=new JSONArray();
        for(int i=0;i<Value.length;i++)
            jarr.add(Value[i]);

        o1.put("Values",jarr);

        return o1.toString();
    }
    public String json_encode_PersonInsert(String secondName,String firstName,String birthDate,String CNP,String username,
                                           String password,String role,String createdBy,String salt)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","PersonInsert");
        o1.put("SecondName",secondName);
        o1.put("FirstName",firstName);
        o1.put("BirthDate",birthDate);
        o1.put("CNP",CNP);
        o1.put("Username",username);
        o1.put("Password",password);
        o1.put("Role",role);
        o1.put("CreatedBy",createdBy);
        o1.put("Salt",salt);

        System.out.println(o1);
        return o1.toString();
    }
    public String json_encode_BookInsert(String title,String author,String numberOfPages,String publicationDate,String acquisitionDate,
                             String type,String numberOfVolumes,String shelf,String section,String bookURL)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","BookInsert");
        o1.put("Title",title);
        o1.put("Author",author);
        o1.put("NumberOfPages",numberOfPages);
        o1.put("PublicationDate",publicationDate);
        o1.put("AcquisitionDate",acquisitionDate);
        o1.put("Type",type);
        o1.put("NumberOfVolumes",numberOfVolumes);
        o1.put("Shelf",shelf);
        o1.put("Section",section);
        o1.put("BookURL",bookURL);


        return o1.toString();
    }
    public String json_encode_BorrowRequestInsert(String username,String dataRequest,String cod,String carteFizica)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","BorrowRequestInsert");
        o1.put("Username",username);
        o1.put("DataRequest",dataRequest);
        o1.put("Cod",cod);
        o1.put("CarteFizica",carteFizica);

        return o1.toString();
    }
    public String json_encode_BooksListing(String column, String value)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","BooksListing");
        o1.put("Column",column);
        o1.put("Value",value);

        return o1.toString();
    }
    public String json_encode_DeleteBook(int ID)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","DeleteBook");
        o1.put("ID",ID);

        return o1.toString();
    }
    public String json_encode_GetNumberOfRows(String tableName)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","GetNumberOfRows");
        o1.put("Table",tableName);

        return o1.toString();
    }

    public String json_encode_GetNumberOfRowsByColumn(String tableName,String Column,String Value)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","GetNumberOfRowsByColumn");
        o1.put("Table",tableName);
        o1.put("Column",Column);
        o1.put("Value",Value);
        return o1.toString();
    }

    public String json_encode_UpdateValue(String tableName,String setColumn,String setValue,String conditionColumn,String conditionValue)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","UpdateValue");
        o1.put("TableName",tableName);
        o1.put("SetColumn",setColumn);
        o1.put("SetValue",setValue);
        o1.put("ConditionColumn",conditionColumn);
        o1.put("ConditionValue",conditionValue);

        return o1.toString();

    }
    public String json_encode_BorrowInsert(String username,String dateBorrow,String dateRetur,String bookFormat,String realReturDate,String aspect,String librarian)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","BorrowInsert");
        o1.put("Username",username);
        o1.put("DateBorrow",dateBorrow);
        o1.put("DateRetur",dateRetur);
        o1.put("BookFormat",bookFormat);
        o1.put("RealReturDate",realReturDate);
        o1.put("Aspect",aspect);
        o1.put("Librarian",librarian);

        return o1.toString();

    }
    public String json_encode_BorrowInsertHash(String username,String dateBorrow,String dateRetur,String bookFormat,String realReturDate,String aspect,String librarian,String hash)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","BorrowInsertHash");
        o1.put("Username",username);
        o1.put("DateBorrow",dateBorrow);
        o1.put("DateRetur",dateRetur);
        o1.put("BookFormat",bookFormat);
        o1.put("RealReturDate",realReturDate);
        o1.put("Aspect",aspect);
        o1.put("Librarian",librarian);
        o1.put("Hash",hash);

        return o1.toString();
    }
    public String json_encode_SelectWithinRange(String tableName,int start,int end)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","SelectWithinRange");
        o1.put("TableName",tableName);
        o1.put("Start",start);
        o1.put("End",end);

        return o1.toString();
    }
    public String json_encode_InnerSelect(String table1,String table2,String condition1,String condition2)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","InnerSelect");
        o1.put("Table1",table1);
        o1.put("Table2",table2);
        o1.put("Condition1",condition1);
        o1.put("Condition2",condition2);

        return o1.toString();
    }
    public String json_encode_InnerSelect_twoConditions(String table1,String table2,String condition1,String condition2,String condition3,String condition4,String interestColumn1,String interestColumn2){

        JSONObject o1=new JSONObject();
        o1.put("Action","InnerSelect_twoConditions");
        o1.put("Table1",table1);
        o1.put("Table2",table2);
        o1.put("Condition1",condition1);
        o1.put("Condition2",condition2);
        o1.put("Condition3",condition3);
        o1.put("Condition4",condition4);
        o1.put("IntersectColumn1",interestColumn1);
        o1.put("IntersectColumn2",interestColumn2);

        return o1.toString();

    }
    public String json_encode_SelectShelf(String section,int numberOfVolumes)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","SelectShelf");
        o1.put("Section",section);
        o1.put("NumberOfVolumes",numberOfVolumes);

        return o1.toString();
    }
    public String json_encode_SelectShelfById(int idToBeErased)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","SelectShelfByID");
        o1.put("IdToBeErased",idToBeErased);

        return o1.toString();
    }
    public String json_encode_ActionInsert(String action)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","ActionInsert");
        o1.put("Actiune",action);

        return o1.toString();
    }
    public String json_encode_LoguriActiuniInsert(int idUser,int idAction,String dateHour)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","LoguriActiuniInsert");
        o1.put("IdUser",idUser);
        o1.put("IdAction",idAction);
        o1.put("DateHour",dateHour);

        return o1.toString();
    }
    public String json_encode_InnerActiuniLoguriActiuniSelect(int id)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","InnerActiuniLoguriActiuniSelect");
        o1.put("ID",id);

        return o1.toString();
    }
    public String json_encode_SelectTopTen(String tableName)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","SelectTopTen");
        o1.put("TableName",tableName);

        return o1.toString();
    }
    public String json_encode_SelectTopTenCondition(String tableName,String orderCondition)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","SelectTopTenCondition");
        o1.put("TableName",tableName);
        o1.put("OrderCondition",orderCondition);

        return o1.toString();

    }
    public String json_encode_BookAllInfoListing(String columnName,String value)
    {
        JSONObject o1=new JSONObject();
        o1.put("Action","BookAllInfoListing");
        o1.put("ColumnName",columnName);
        o1.put("Value",value);

        return o1.toString();

    }

}
