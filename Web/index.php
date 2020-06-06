<!DOCTYPE html>
<html>
    <head>
    <link href="style1.css" rel="stylesheet">    
    <link href='https://fonts.googleapis.com/css?family=Aldrich' rel='stylesheet'>
    <title>SPACE INVADERS START</title>
    </head>
    
    <body>    
        <form method="post" action="game.php">
            
                <div class="Title" style="text-align:center;">SPACE INVADERS</div>
                <div class="Under" style="text-align:center;">*please enter your name and select a ship to start*</div>
            NAME: <input type="text" id="name" name="name" required><br><br>
            
            SHIP:
                  <br><input type="radio" id="default" name="shipType" value="default" required>
                  <label for="blue_choice" style="color:blue;">Blue</label><br>
                  <input type="radio" id="default" name="shipType" value="default" required>
                  <label for="green_choice" style="color:green;">Green</label><br>
                  <input type="radio" id="default" name="shipType" value="default" required>
                  <label for="red_choice" style="color:red;">Red</label><br>
                  <input type="radio" id="default" name="shipType" value="default" required>
                  <label for="yellow_choice" style="color:yellow;">Yellow</label><br><br>
            <input type="submit" value="SUBMIT">
        </form>

        <!-- <?php
            $servername = "209.129.8.7";
            $username = "RCCCSCCIS17B";
            $password = "4050240368";
            $dbname = "RCCCSCCIS17B";

            $nameP = $_GET['name'];

            // Create connection
            $conn = new mysqli($servername, $username, $password, $dbname);
            // Check connection
            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
            }

            $sql = "INSERT INTO spaceinvaders_entity_player (name)
            VALUES (DEFAULT, $nameP)";

            if ($conn->query($sql) === TRUE) {
                echo "New record created successfully";
            } else {
                echo "Error: " . $sql . "<br>" . $conn->error;
            }
        ?> -->
    </body>
</html>
