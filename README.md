# Hack Money

**A Hack Library for dealing with money and currency conversion**

[![Latest Stable Version](https://poser.pugx.org/apoyan/hack-money/v/stable)](https://packagist.org/packages/apoyan/hack-money) [![Total Downloads](https://poser.pugx.org/apoyan/hack-money/downloads)](https://packagist.org/packages/apoyan/hack-money) [![Latest Unstable Version](https://poser.pugx.org/apoyan/hack-money/v/unstable)](https://packagist.org/packages/apoyan/hack-money) [![License](https://poser.pugx.org/apoyan/hack-money/license)](https://packagist.org/packages/apoyan/hack-money)

## Installation

Hack Money is installed via [Composer](http://getcomposer.org/). To install, simply add it
to your `composer.json` file:

```json
{
    "require": {
        "apoyan/hack-money": "~1.0"
    }
}
```

And run composer to update your dependencies:

    $ curl -s http://getcomposer.org/installer | php
    $ php composer.phar update

## Usage

```php

<?php
use Money\Money as Money;

# Money
$currency = new Currency('USD');

$money = new Money(10.00, $currency);
$money_2 = new Money('10.00', $currency);
$money = new Money(10, "EUR");
$money = new Money(10.00, "USD");

$money->getAmount(); // => 10.00
$money->getCurrency(); // => "USD"

# Comparisons
$money->equals($money_2); // => false
$money->equals($money); // => true
$money->isSameCurrency($money_2); // => true

# Arithmetic
$money->add($money_2)->getAmount(); // => "110.00"
$money->sub(new Money(10, "USD"))->getAmount(); // => "10.00"
$money->div(new Money(10, "EUR"))->getAmount(); // => "Exception: Currencies must be identical"
$money->mul(new Money(2, "USD"))->getAmount(); // => "20.00"

# Formatting

$currency = new Currency('USD');
$money = new Money("1000000.00", $currency);

$money->format(
  [
    "with_currency" => true,
    "no_cents_if_whole" => true,
    "thousands_separator" => ' ',
    "decimal_mark" => ',',
    "with_symbol" => true,
    "symbol_position" => "before"
  ]
); // => "$1 000 000 USD"
```

## Currency

``` php
<?php
$currency = new Currency('USD');
$currency_2 = new Currency('EUR');
$currency_3 = new Currency('USD');

$currency->getCode(); // => "USD"
$currency->getName(); // => "United States Dollar"
$currency->getSymbol(); // => "$"
$currency->exponent(); // => 2

$currency->equals($currency_2); // => false
$currency->equals($currency_3); // => true
$currency->equals("USD"); // => true

```
