package ro.mta.library_project.Communication;


import javax.crypto.spec.DHParameterSpec;
import java.math.BigInteger;
import java.security.AlgorithmParameterGenerator;
import java.security.AlgorithmParameters;
import java.security.NoSuchAlgorithmException;
import java.security.spec.InvalidParameterSpecException;

public class MyDHKeyAgreement {
    private DHParameterSpec dhSpec;
    public MyDHKeyAgreement(int numBits) throws NoSuchAlgorithmException, InvalidParameterSpecException {
        AlgorithmParameterGenerator paramGen = AlgorithmParameterGenerator.getInstance("DH");
        paramGen.init(numBits);

        AlgorithmParameters params = paramGen.generateParameters();
        this.dhSpec = (DHParameterSpec) params.getParameterSpec(DHParameterSpec.class);
        //p=modulus, g=generatorul(baza care e ridicata la putere), l=exponent
    }
    public BigInteger getMyP()
    {
        return dhSpec.getP();
    }
    public BigInteger getMyG()
    {
        return dhSpec.getG();
    }
    public int getMyL()
    {
        return dhSpec.getL();
    }
}
