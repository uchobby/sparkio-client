sparkjs David Folwer AKA uCHobby 11/24/2014
=======
Spark io JavaScript library for browser based application development.
Available at https://github.com/uchobby/sparkjs

You can use this code for anything you wish, there no ties or warrantees.
Send me an email if you have any suggestions or to let me know what you think.
david.fowler@gmail.com

This simple JavaScript library has two methods which make getting variables and calling function
on your Spark cord simple.

constructor SparkAPI(deviceID,accessToken)
    Creates the SparkAPI object using your deviceID and token. Use new to create as many as you need.
    The deviceID and token values are found in the Spark IDE, one under "cores" and the other in "settings"
    
    Parameters:
        deviceID
            String with your device ID.
        accessToken
            String with your accessToken.

getVariable(variableName,callback)
    Calls the API for a registered variable. Call with nothing to get a basic status response.
    Uses the deviceID and accessToken, with an HTTP GET to the Spark server.
    
    Parameters:
        variableName
            Registered Spark device variable name
        callback
            Function to call when response arrives
            Callback is passed the result object. 
                callback(result);
    return:
        void

callFunction(functionName, paramString, callback)
    Calls the API for a registered Spark function. 
    Uses the deviceID and accessToken, with an HTTP POST to the Spark server.
    
    Parameters:
        functionName
            Registered Spark device function name
        paramString
            A string of text to pass as parameters for the Spark function 
        callback
            Function to call when response arrives
            Callback is passed the result object. 
                callback(result);
    return:
        void

To Use:
    var SparkDevice=new SparkAPI(deviceID,accessToken);         /
    
    SparkDevice.getVariable("",onSparkStatus);                  //Get a variable with "" as the name, actually pulls status.
    
    function onSparkStatus(result) {                                //Callback function for the status button
        console.log("Get Status Response:"+JSON.stringify(result)); //Just dump the result object to the console. Use the JS console
    }                                                               //to view result. Could do a lot of stuff but keeping it simple now.

*****************************
Important note about Security
*****************************
This example code has security issues! The index.html example puts your deviceID and accessToken at risk.  If you were to put this code up on a web site, any one could view the code to find your access info. Probably not a big deal if your just showing some value or using it for simple testing, privately. If your core is controlling something critical, you could be in danger if you expose code like this to the public.

This code is meant as an example, not as a guide for how you would manage security in your web app. The advice given is free and I'm not claiming it's worth what you paid for it.

For a simple web app, you might let the user enter the deviceID and accessToken into the app. This data can be saved in local storage so the user only needs to do it once. When your app starts it reads the local stored values and comes up ready to go. This is reasonably secure as the codes are kept on the user's machine. There is still some risk as they will be sent in the HTTP request, in the clear, but the risk maybe low.

If you are making a product to sell, you will need keep this code only on a protected server. This server would proxy all communications with user level security. This way you don’t expose the keys, as long as your server code is safe.

Spark core access keys can be reset at any time. Just log in and click the reset button in the same area where you find your key.  If you share your code, and forget to edit out the key, go do this reset.

For home projects a simple level of security would be to host your web app on a web server where log in is required to get at it.  This should be easy to do on most web servers but I will not go into that here.
