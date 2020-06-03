<!DOCTYPE html>
<html>
    <body>
        <form method="post" action="game.php">
            Name: <input type="text" id="name" name="name" required><br><br>
            Ship: <br><input type="radio" id="default" name="shipType" value="Blue" required>
                  <label for="blue_choice">Blue</label><br>
                  <input type="radio" id="default" name="shipType" value="Green" required>
                  <label for="green_choice">Green</label><br>
                  <input type="radio" id="default" name="shipType" value="Red" required>
                  <label for="red_choice">Red</label><br>
                  <input type="radio" id="default" name="shipType" value="Yellow" required>
                  <label for="yellow_choice">Yellow</label><br><br>
            <input type="submit" value="Submit">
        </form>
    </body>
</html>