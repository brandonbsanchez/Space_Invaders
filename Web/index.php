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
    </body>
</html>