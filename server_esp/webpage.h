const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
      <meta charset="UTF-8">
      <title>Web Mekatroniks</title>
      <link rel="stylesheet" href="style.css">
      <link href="https://fonts.googleapis.com/css2?family=Bungee&family=Montserrat:wght@100&display=swap"
            rel="stylesheet">
      <link href="https://fonts.googleapis.com/css2?family=Bungee&family=Montserrat:wght@100;300&display=swap"
            rel="stylesheet">
      <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.1.0/css/all.min.css">
      <style>
      *{
  padding: 0;
  margin : 0;
  text-decoration:none;
  list-style-type: none;
}
body{
  margin: 0;
  padding:0;
  font-family:'Open Sans',sans-serif;
  background-image: .background
  background-size: cover;
}
nav .wrapper{
 width: 1100%;
 margin: 0px;
}
nav .logo a{
  font-size: 60px;
  font-weight:bold;
  float: left;
  font-family: courier;
  color: rgb(253, 252, 252);
  margin-right: auto;
}
nav{
  width: 90%;
  margin: auto;
  display: flex;
  line-height: 80px;
  position: sticky;
  position: -webkit-sticky;
  top: 0;
}
nav ul{
 margin-left: 100px;
 padding: 0px;
}
nav ul li {
  float: right;
  overflow: hidden;
}
nav ul li a{
  color:#46F8F8 ;
  font-family: 'Montserrat', sans-serif;
  font-size: 30px;
  padding-right: 50px;
  text-decoration: none;
}
nav ul li a:hover{
 color:#F36F2D;
 text-decoration: underline;
}
.judul{
  position: relative;
  font-size: 50px;
  margin-top: 350px;
  text-align: center;
  color:#F36F2D ;
  margin:300px 340px;
}
.judul h1{
 font-family: 'Montserrat', sans-serif;
 display:inline;
 justify-content: center;
 align-items: center;
}
.judul ul li{
  align-content: center;
  color:rgb(253, 252, 252);
  size: 30px;
  position:relative;
  display: inline-flex;
  margin-right: 20px;
}
p{
  color:rgb(253, 252, 252);
  font-size: 30px;
  font-weight: bold;
  font-style: italic;
  font-family: 'Montserrat', sans-serif;
  display: flex;
  justify-content: center;
  align-content: center;
}
      </style>
</head>

<body> 
         <nav>
            <div class="wrapper">
                  <div class="logo"><a href="profile">TEKNISI WIBU</a></div>
                  <ul>
                        <li><a href="home">HOME</a></li>
                        <li><a href="product">PRODUCT</a> </li>
                        <li><a href="news">NEWS</a></li>
                        <li><a href="blog">BLOG</a>
                        </li>
                  </ul>
            </div>
      </nav>
      <div class="judul">
            <h1>welcome to my website</h1>
            <ul>
                  <li><i class="fa-solid fa-book-journal-whills"></i></li>
                  <li><i class="fa-solid fa-code"></i></li>
                  <li><i class="fa-solid fa-gamepad"></i></li>
            </ul>
      </div>
      <p>Copyright &copy; LAB Mekatroniks</p>
</body>

</html>
)=====";
