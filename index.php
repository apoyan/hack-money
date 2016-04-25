<?php

require_once "./src/Currency/Loader.php";
use Money\Currency\Loader;

print_r(Loader::load_currencies());
