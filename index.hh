<?hh // decl

require_once "./src/Currency/Loader.hh";
require_once "./src/Currency/Currency.hh";
require_once "./src/Money/BigDecimal.hh";
require_once "./src/Money/Formatter.hh";
require_once "./src/Money.hh";
require_once "./src/Exception/CurrencyException.hh";
require_once "./src/Exception/MoneyException.hh";

use Money\Money;
use Money\Currency\Loader;
use Money\Currency\Currency;
use Money\Money\BigDecimal;


$currency = new Currency('USD');
$currency_2 = new Currency('EUR');

$money = new Money("-1000000.00", $currency);
$money_2 = new Money('100', $currency);

// $m = new Money($money);
// $m->format();
print_r($money->format(
  [
    "sign" => true,
    "with_currency" => true,
    "no_cents_if_whole" => true,
    "thousands_separator" => ' ',
    "decimal_mark" => ',',
    "with_symbol" => true,
    "symbol_position" => "before"
  ]
));
