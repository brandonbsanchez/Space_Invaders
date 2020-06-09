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
                <div class="Under" style="text-align:center;">*A = Left. D = Right. Spacebar = Shoot*</div>
            <?php
            //Check for errors in username:
            if(isset($_GET['error']) == 'invalidusername'){ //If invalidusername, alert user:
                echo '<p id="error">Invalid entry: Enter only alpha-numeric characters.</p>';
            }
                echo 'Name:'; if(isset($_COOKIE['name'])){
                    echo '<input type="text" id="name" name="name" value="' . $_COOKIE["name"] . '" required><br><br>';
                } else{
                    echo '<input type="text" id="name" name="name" require><br><br>';
                }
            ?>
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
    </body>
</html>
