<!DOCTYPE html>
<html>
    <body>
        <form method="post" action="game.php">
            Name: <input type="text" id="name" name="name" required><br>
            Ship: <input type="radio" id="default" name="shipType" value="default" required>
                  <label for="default">Default</label><br>
            <input type="submit" value="Submit">
        </form>
    </body>
</html>