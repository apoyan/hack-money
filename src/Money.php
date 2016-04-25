<?php

namespace Money;
use Money\Currency\Currency;
use Money\Money\Calculator;
use Money\Money\Formatter;

class Money {
  private $calculator;
  private $formatter;
  private $currency;
  private $cents;

  public function __construct() {
    $this->calculator = new Calculator();
    $this->formatter = new Formatter();
    $this->currency = $currency;
  }

  public function cents() {

  }

  public function currency() {
    return $this->currency;
  }

  public function equals(Money $other) {
    return $this->isSameCurrency($other) && $this->cents === $other->cents;
  }

  public function add(Money $other) {

  }

  public function sub(Money $other) {

  }

  public function mul(Money $other) {

  }

  public function div(Money $other) {

  }

  public function format() {

  }

  public function isSameCurrency(Money $other) {
        return $this->currency->equals($other->currency);
  }
}
