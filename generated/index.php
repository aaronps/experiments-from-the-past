<?php
    echo '<?xml version="1.0" encoding="UTF-8"?>';
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
        <title>Project List</title>
        <link rel="stylesheet" type="text/css" href="style.css" />
</head>
<body>
<h1>Project List</h1>
<table>
<tr><th>Project</th><th>Last commit</th><th>Report of Commit</th></tr>
<?php
# the correct header should be strict, but strict doesn't have <input>
# 2016-11-25 WTF who would remember that!!! it has input but has to be wrapped around other tags
# <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

    foreach ( glob("*") as $repfile )
    {
        if ( is_dir($repfile) )
        {
            $indexfile = $repfile . "/index.html";
            $cmd = "grep -A 1 'Head revision' $indexfile | tail -n 1  | cut -f 2 -d '>' | cut -f 1 -d '<'";
            $cver = exec( $cmd );

            $repname = basename($repfile);
            #$latestver = file_get_contents( "/svn/svnstats/cache/" . $repname );
            $latestver = exec( "svnlook youngest /data/svn/repos/svn/" . $repname );

            if ( $cver > 0 )
            {
                $setclass = " class='greenbg'";
                if ( (int)$cver != (int)$latestver )
                {
                    $setclass = " class='redbg'";
                }

                if ( is_dir( "../work/$repfile" ) )
                {
                    $setclass = " class='yellowbg'";
                }

                echo "<tr$setclass><td><a href='$repname'>$repname</a></td><td>$latestver</td><td>$cver</td></tr>";
            }
            else
            {
                echo "<tr><td>$repname</td><td>0</td><td>0</td></tr>";
            }
        }
    }
?>

</table>
<form name="regenerateForm" action="regenerate.php" target="_blank">
    <input type="submit" value="Regenerate statistics" />
</form>
</body></html>
