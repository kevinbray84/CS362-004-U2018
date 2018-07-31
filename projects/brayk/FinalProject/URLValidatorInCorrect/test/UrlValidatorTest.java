

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   UrlValidator urlVal = new UrlValidator(null, null, 0L);
	   boolean isValid;
	   boolean allPassed = true;
	   boolean expected = true;
	   String url;
	   
	   String goodUrl[] = {	           
			   "http://www.google.com",
			   "http://www.cnn.com:80",
			   "http://www.asdf.biz",
			   "http://www.google.com:0",
			   "http://www.google.com:80",
			   "http://www.google.com:800",
			   "http://www.google.com:8000",
			   "http://www.google.com:65535",
			   "http://www.google.com:80",
			   "http://www.google.com",
			   "ftp://www.google.com",		
			   "https://www.google.com",
			   "https://www.google.com/",
			   "https://www.google.com:80/",
			   "https://www.google.com/search",
			   "https://www.google.com/search.html",
			   "https://www.google.com/?asdf=fdas",
			   "https://www.google.com/?%20",
			   "https://www.google.com/?asdf$",			   
			   "https://www.google.com/?asd%20fdsa",
			   "http://www.geocities.com/nkotb_fan_club",			   
			   "http://www.geocities.com/~nkotb_fan_club",							// ~ failing test
			   "http://192.168.1.1", 
			   "http://192.168.1.0", 
			   "http://0.0.0.0", 
			   "http://255.255.255.255", 
			   "http://192.168.1.1:80",
			   "http://[FEDC:BA98:7654:3210:FEDC:BA98:7654:3210]:80/index.html",
		       "http://[1080:0:0:0:8:800:200C:417A]/index.html",
	           "http://[3ffe:2a00:100:7031::1]",
	           "http://[1080::8:800:200C:417A]/foo",
	           "http://[2010:836B:4179::836B:4179]"
	   };
	   
	   String badUrl[] = {
			   "asdf",
			   "junk://www.google.com",
			   "http://www.google.com:65536",
			   "http://www.google.com:65536/",
			   "https://www.google.com/?asd fdsa",
			   "http://192.168.1.256", 
			   "http://192.168.256.256", 
			   "http://256.257.258.259", 
			   "http://256.256.256.256", 
			   "http://192.168.1.256:80",
			   "http://FEDC:BA98:7654:3210:FEDC:BA98:7654:3210:80/index.html",
		       "http://1080:0:0:0:8:800:200C:417A/index.html",
	           "http://3ffe:2a00:100:7031::1",
	           "http://1080::8:800:200C:417A/foo",
	           "http://2010:836B:4179::836B:4179"	   
	   };
	   
	   System.out.println("**************  MANUAL TESTING  **************");
	   System.out.println("PASS/FAIL | EXPECTED | ACTUAL | URL");
	   System.out.println("----------------------------------------------------");
	   
	   for (int i = 0; i < goodUrl.length; i++) {
		   url = goodUrl[i];
		   isValid = urlVal.isValid(url);
		   expected = true;
		   if (isValid == expected) {
			   System.out.print("PASSED    | ");
		   } else {
			   System.out.print("FAILED    | ");
		   }
		   System.out.print("VALID    | ");
		   if (isValid) {
			   System.out.print("VALID   | ");
			   System.out.println(url);
		   } else {
			   System.out.print("INVAL   | ");
			   System.out.println(url);
			   allPassed = false;
		   }
	   }
	   
	   System.out.print("\n");
	   
	   for (int i = 0; i < badUrl.length; i++) {
		   url = badUrl[i];
		   isValid = urlVal.isValid(url);
		   expected = false;
		   if (isValid == expected) {
			   System.out.print("PASSED    | ");
		   } else {
			   System.out.print("FAILED    | ");
		   }
		   System.out.print("INVAL    | ");
		   if (isValid) {
			   System.out.print("VALID   | ");
			   System.out.println(url);
			   allPassed = false;
		   } else {
			   System.out.print("INVAL   | ");
			   System.out.println(url);
		   }
	   }
	   
	   assertTrue(allPassed);
   }
	   

   
   public void testScheme()
   {
	 //You can use this function to implement your First Partition testing	   

	   boolean isValid;
	   boolean allPassed = true;
	   boolean expected;
	   String scheme;
	   
	  // *** Test scheme component ***
	   String goodSchemes[] = {
			   "http",
			   "https",
			   "ftp",
	   };
	   
	   String badSchemes[] = {
			   "asdffdsa",
			   "3ht",
			   "asdf"
	   };
	   
	   // using this constructor allows you to pass in a list of good schemes.  
	   // the 0L flag gives no options such as ALLOW_ALL_SCHEMES or ALLOW_2_SLASHES
	   UrlValidator urlVal = new UrlValidator(goodSchemes, 0L);
	   
	   System.out.println("\n**************  TESTING SCHEME COMPONENTS **************");
	   System.out.println("PASS/FAIL | EXPECTED | ACTUAL | SCHEME");
	   System.out.println("----------------------------------------------------");
	   
	   for (int i = 0; i < goodSchemes.length; i++) {
		   scheme = goodSchemes[i];
		   isValid = urlVal.isValidScheme(scheme);
		   expected = true;
		   if (isValid == expected) {
			   System.out.print("PASSED    | ");
		   } else {
			   System.out.print("FAILED    | ");
		   }
		   System.out.print("VALID    | ");
		   if (isValid) {
			   System.out.print("VALID  | ");
			   System.out.println(scheme);
		   } else {
			   System.out.print("INVAL  | ");
			   System.out.println(scheme);
			   allPassed = false;
		   }
	   }
	   
	   System.out.print("\n");
	   
	   for (int i = 0; i < badSchemes.length; i++) {
		   scheme = badSchemes[i];
		   isValid = urlVal.isValidScheme(scheme);
		   expected = false;
		   if (isValid == expected) {
			   System.out.print("PASSED    | ");
		   } else {
			   System.out.print("FAILED    | ");
		   }
		   System.out.print("INVAL    | ");
		   if (isValid) {
			   System.out.print("VALID  | ");
			   System.out.println(scheme);
			   allPassed = false;
		   } else {
			   System.out.print("INVAL  | ");
			   System.out.println(scheme);
		   }
	   }
	   
	   assertTrue(allPassed);

   }
   
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
