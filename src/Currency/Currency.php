<?php

namespace Money\Currency;
use Money\Loader;

class Currency {
  private $data;
  private $decimal_mark;
  private $disambiguate_symbol;
  private $html_entity;
  private $iso_code;
  private $iso_numeric;
  private $name;
  private $priority;
  private $smallest_denomination;
  private $subunit;
  private $subunit_to_unit;
  private $symbol;
  private $symbol_first;
  private $thousands_separator;

  public function __construct($id) {
    $this->data = Currency::table[$id];
    $decimal_mark          = data["decimal_mark"]
    $disambiguate_symbol   = data["disambiguate_symbol"]
    $html_entity           = data["html_entity"]
    $iso_code              = data["iso_code"]
    $iso_numeric           = data["iso_numeric"]
    $name                  = data["name"]
    $priority              = data["priority"]
    $smallest_denomination = data["smallest_denomination"]
    $subunit               = data["subunit"]
    $subunit_to_unit       = data["subunit_to_unit"]
    $symbol                = data["symbol"]
    $symbol_first          = data["symbol_first"]
    $thousands_separator   = data["thousands_separator"]
  }
  public function getCode() {
    return $this->iso_code;
  }

  public function getName() {
    return $this->name;
  }

  public function __toString() {
    return $this->getCode();
  }

  public function equals(Currency $other_currency) {
    return $this->iso_code === $other_currency->iso_code;
  }

  public function exponent() {
    return round(log10($subunit_to_unit));
  }

  private static function table() {
    $this->table = Loader::load_currencies();
  }
}
