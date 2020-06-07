<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>Space Invaders</title>
        <link href='https://fonts.googleapis.com/css?family=Aldrich' rel='stylesheet'>
        <link href="styles.css" rel="stylesheet">
        <?php 
            $cookie_name = "name";
            setcookie($cookie_name, $_POST['name'], time() + (86400 * 30), "/");
        ?>
    </head>
    <body>
    <div id="Title" style="text-align:center;">SPACE INVADERS</div>
        <div id="container">
                <div id="leaderboard">
                    <div id="S">Score:</div>
                    <div id="score">0</div>
                </div>
            <div id="board"></div>
            <div id="lives">    
            <?php echo '<img id="icon" src="Images/' . $_POST['shipType'] . '" height="25" width="25">'; ?> <span id="livesLeft">3</span>
            </div>
            <div id="won">
                <h1>Congratulations!</h1>
                <h2>You won.</h2>
                <br>
                <form method="POST" action="leaderboard.php">
                    <button id="ldrBrdBtn0" name="ldrBrdBtn0" type="submit" value=0>View Leaderboard</button>
                </form>
            </div>
            <div id="lost">
                <h1>Game over.</h1>
                <h2>You lost.</h2>
                <br>
                <form method="POST" action="leaderboard.php">
                    <button id="ldrBrdBtn1" name="ldrBrdBtn1" type="submit" value=0>View Leaderboard</button>
                </form>
            </div>
        </div>

        <script src="app.js"></script>

        <?php  
            session_start();

            $_SESSION['name'] = $_POST['name'];
            $_SESSION['shipColor'] = $_POST['shipType'];

            switch($_POST['shipType']){
                case "Blue":
                    $_SESSION['shipType'] = 1;
                    break;
                case "Green":
                    $_SESSION['shipType'] = 2;
                    break;
                case "Red":
                    $_SESSION['shipType'] = 3;
                    break;
                case "Yellow":
                    $_SESSION['shipType'] = 4;
                    break;
            }
        ?>
    </body>
</html>
