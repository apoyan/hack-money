<?php

require_once "./src/Currency/Loader.php";
require_once "./src/Currency/Currency.php";
require_once "./src/Money/Calculator.php";
require_once "./src/Money/BigDecimal.php";
require_once "./src/Money/Formatter.php";
require_once "./src/Money.php";
require_once "./src/Exception/CurrencyException.php";
require_once "./src/Exception/MoneyException.php";

use Money\Money;
use Money\Currency\Loader;
use Money\Currency\Currency;


$currency = new Currency('USD');
$money = new Money('0.12', $currency);
$m = new Money($money);
print_r($m->cents());
// print_r(new Money('1.00'));
// $table = null;
// if($table === null) {
//   $table = Loader::load_currencies();
// }
//
// print_r($table["usd"]);
