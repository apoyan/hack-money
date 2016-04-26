<?php

namespace Money;
use Money\Currency\Currency;
use Money\Money\Calculator;
use Money\Money\Formatter;
use Money\Exception\CurrencyException;
use Money\Exception\MoneyException;
use Money\Money\BigDecimal as BigDecimal;

class Money {
  private $calculator;
  private $formatter;
  private $currency;
  private $_cents;

  public function __construct($obj, Currency $currency = null) {
    if($obj instanceof Money) {
      $this->_cents = $obj->cents();
      $this->currency = $obj->currency();
    } else {
      $this->_cents = new BigDecimal($obj);
    }

    $this->calculator = new Calculator();
    $this->formatter = new Formatter();
  }

  public function cents() {
    return $this->_cents;
  }

  public function amount() {
    return to_amount($this->cents);
  }

  public function currency() {
    return $this->currency;
  }

  public function equals(Money $other) {
    return $this->isSameCurrency($other) && $this->cents === $other->cents;
  }

  public function add(Money $other) {
    $this->assertSameCurrency($addend);
    return new self($this->calculator->add($this->cents, $other->cents), $this->currency);
  }

  public function sub(Money $other) {
    $this->assertSameCurrency($addend);
    return new self($this->calculator->subtract($this->cents, $other->cents), $this->currency);
  }

  public function mul(Money $other) {
    $this->assertSameCurrency($addend);
    return new self($this->calculator->multiply($this->cents, $other->cents), $this->currency);
  }

  public function div(Money $other) {
    $this->assertSameCurrency($addend);
    return new self($this->calculator->divide($this->cents, $other->cents), $this->currency);
  }

  public function format() {

  }

  public function isSameCurrency(Money $other) {
        return $this->currency->equals($other->currency);
  }

  private function assertSameCurrency(Money $other) {
    if (!$this->isSameCurrency($other)) {
      throw new \CurrencyException('Currencies must be identical');
    }
  }

  private function to_amount($cents) {

  }

  private function to_cents($amount) {

  }
}
