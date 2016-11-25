<?php
        echo '<?xml version="1.0" encoding="UTF-8"?>';
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
        <title>Stats Regeneration</title>
        <link rel="stylesheet" type="text/css" href="style.css" />
</head>
<body>
<h1>Stats regeneration</h1>
<?php
        $cmd = "ps -C run-stats-full.sh";

        exec( $cmd, $output, $result);
        unset( $output );

        if ( $result == 0 )
        {
                echo '<h2>Program is already running</h2>';
        }
        else
        {
                exec ( "/data/applications/statsvn/bin/run-stats-full.sh > /dev/null 2>&1 &", $output, $result);
                echo '<h2>Launched regeneration</h2>';
        }
?>
<p>You can close this window now</p>
</body></html>