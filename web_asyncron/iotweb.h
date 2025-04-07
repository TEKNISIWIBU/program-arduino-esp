const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
    h1 {
        color: #0F3376;
        padding: 2vh;
    }

    p {
        font-size: 1.5rem;
    }

    .button {
        display: inline-block;
        background-color: #008CBA;
        border: none;
        border-radius: 4px;
        color: white;
        padding: 16px 40px;
        text-decoration: none;
        font-size: 30px;
        margin: 2px;
        cursor: pointer;
    }

    .button2 {
        background-color: #f44336;
    }
  </style>
</head>
<body>
  <h2>ESP8266 DHT Server</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">VOLT</span> 
    <span id="VOLT">%VOLT%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <!--relay-->
    <p>status relay:<strong class="relay"></strong></p>
    <p>
        <a onclick="onrelay()"><button class="button">ON</button></a>
        <a onclick="offrelay()"><button class="button button2">OFF</button></a>
    </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("VOLT").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/VOLT", true);
  xhttp.send();
}, 5000 ) ;

</script>
</html>)rawliteral";