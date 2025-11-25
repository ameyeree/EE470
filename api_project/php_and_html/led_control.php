<!DOCTYPE HTML>
<html>
    <head>
        <title>LED Sensor Page</title>
        <style>
            body {
                margin: 0;
                padding: 0;
                background-color: CadetBlue;
                font-family: Tahoma, Verdana, sans-serif;
            }
            header {
                width: 100%;
                margin: 0;
                background-color: DarkSlateGray;
                padding: 20px;
                color: white;
            }
            h1, h2 {
                margin: 0;
            }
            a {
                color: DeepSkyBlue;
            }
            div {
                border-radius: 15px 50px;
                background-color: DarkSlateGray;
                padding: 20px;
                width: 750px;
                height: auto;
                margin: 20px auto;
                color: white;
                
                display: flex;
                flex-direction: column;
                align-items: center;
            }
        </style>
    </head>
    <body>


        <header>
            <h1>Sonoma State University</h1>
            <h2>Electrical Engineering</h2>
            <p>Welcome to our IoT class!!</p>
            <p>The coolest engineering course ever!</p>
            <p>My name: Anthony Meyer Slechta</p>
        </header>
        <nav id="navbar"></nav>
        <script>
          fetch("navbar2.html")
            .then(res => res.text())
            .then(html => document.getElementById("navbar").innerHTML = html)
            .catch(err => console.error("Navbar load failed:", err));
        </script>
        <br>
        <br>
        <div>
            <h2>Control the LED</h2>
            <ul>
<?php
// Default LED status
$led_status = "off";
$results_file = "results.txt";

// Read current status from results.txt (if it exists)
if (file_exists($results_file)) {
    $file_contents = trim(file_get_contents($results_file));
    if ($file_contents === "on" || $file_contents === "off") {
        $led_status = $file_contents;
    }
}

// Handle submit
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if (isset($_POST["fname"])) {
        $var1 = $_POST["fname"];

        $led_status = $var1;

        $myfile = fopen($results_file, "w") or die("Unable to open file!");
        fwrite($myfile, $var1);
        fclose($myfile);
    }
}
?>

<form method="post" action="<?php echo $_SERVER['PHP_SELF'];?>">
    Click to turn ON: <input type="submit" name="fname" value="on">
    <p> </p>
    Click to turn OFF: <input type="submit" name="fname" value="off">
</form>

<p>Current LED status: <strong><?php echo htmlspecialchars($led_status); ?></strong></p>
            </ul>
        </div>
        <div>
            <u1>
                <iframe width="600" height="371" seamless frameborder="0" scrolling="no" src="https://docs.google.com/spreadsheets/d/e/2PACX-1vTUQ_7NZQh-GFNqwthX3d_XaaLXPwb3OaWuHTtNfuTIw4ucB-XfnE74YkdTXHesh8XtDP7txOpKqTAp/pubchart?oid=1507563104&amp;format=interactive"></iframe>
            </u1>
        </div>
        <br>
        <br>
    </body>
</html>



