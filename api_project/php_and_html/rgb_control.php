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
            <h2>Control the RGB</h2>
            <ul>
                <?php
                    // Default Values
                    $r = 0;
                    $g = 0;
                    $b = 0;
                    
                    // Check if the file exists, and read last saved values to update slider
                    if (file_exists(("rgb.txt"))) {
                        $lines = file("rgb.txt", FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);
                        foreach ($lines as $line) {
                            if (strpos($line, "R:") === 0) {
                                $r = (int)substr($line, 2);
                            } elseif (strpos($line, "G:") === 0) {
                                $g = (int)substr($line, 2);
                            }elseif (strpos($line, "B:") === 0) {
                                $b = (int)substr($line, 2);
                            }
                        }
                    }
                    
                    // Handle for submit
                    if ($_SERVER["REQUEST_METHOD"] == "POST") {
                        $r = isset($_POST["slider1"]) ? $_POST["slider1"] : 0;
                        $g = isset($_POST["slider2"]) ? $_POST["slider2"] : 0;
                        $b = isset($_POST["slider3"]) ? $_POST["slider3"] : 0;
                        
                        $myfile = fopen("rgb.txt", "w") or die("Unable to open file!");
                        fwrite($myfile, "R:" . $r . "\n");
                        fwrite($myfile, "G:" . $g . "\n");
                        fwrite($myfile, "B:" . $b . "\n");
                        fclose($myfile);
                    }
                ?>


                <form method="post" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']);?>">
                    <label for="slider1">Red (0-255): </label>
                    <input type="range" id="slider1" name="slider1" min="0" max="255" value="<?php echo htmlspecialchars($r); ?>" oninput="this.nextElementSibling.value = this.value">
                    <output><?php echo htmlspecialchars($r); ?></output>
                    <p></p>
                    
                    <label for="slider2">Green (0-255): </label>
                    <input type="range" id="slider2" name="slider2" min="0" max="255" value="<?php echo htmlspecialchars($g); ?>" oninput="this.nextElementSibling.value = this.value">
                    <output><?php echo htmlspecialchars($g); ?></output>
                    <p></p>
                    
                    <label for="slider3">Blue (0-255): </label>
                    <input type="range" id="slider3" name="slider3" min="0" max="255" value="<?php echo htmlspecialchars($b); ?>" oninput="this.nextElementSibling.value = this.value">
                    <output><?php echo htmlspecialchars($b); ?></output>
                    <p></p>
                    
                    <input type="submit" value="Submit Values">
                </form>

            </ul>
        </div>
        <br>
        <br>
        <div>
            <u1>
                <iframe width="600" height="371" seamless frameborder="0" scrolling="no" src="https://docs.google.com/spreadsheets/d/e/2PACX-1vTUQ_7NZQh-GFNqwthX3d_XaaLXPwb3OaWuHTtNfuTIw4ucB-XfnE74YkdTXHesh8XtDP7txOpKqTAp/pubchart?oid=1962631885&amp;format=interactive"></iframe>
            </u1>
        </div>
    </body>
</html>







