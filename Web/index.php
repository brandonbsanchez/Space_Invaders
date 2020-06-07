<!DOCTYPE html>
<html>
    <head>
        <link href="styles.css" rel="stylesheet">
    </head>
    <body>
    <form method="post" action="game.php">
            Name: <input type="text" id="name" name="name" required><br><br>
            Ship:
                  <br><input type="radio" name="shipType" value="blue.png" required>
                  <label for="blue_choice"><img class="icon" src="Images/blue.png">Blue</label><br>
                  <input type="radio" name="shipType" value="green.png" required>
                  <label for="green_choice"><img class="icon" src="Images/green.png">Green</label><br>
                  <input type="radio" name="shipType" value="red.png" required>
                  <label for="red_choice"><img class="icon" src="Images/red.png">Red</label><br>
                  <input type="radio" name="shipType" value="orange.png" required>
                  <label for="orange_choice"><img class="icon" src="Images/orange.png">Orange</label><br><br>
            <input type="submit" value="Submit">
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