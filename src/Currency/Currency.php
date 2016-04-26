<?php

namespace Money\Currency;
use Money\Currency\Loader as Loader;

class Currency {
  private $data = array();
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
  private static $table = null;

  public function __construct($id) {
    if(!isset($table)) {
      Currency::$table = Loader::load_currencies();
    }
    $this->data = Currency::$table[strtolower($id)];
    $this->decimal_mark          = $this->data["decimal_mark"];
    // $this->disambiguate_symbol   = $this->data["disambiguate_symbol"];
    $this->html_entity           = $this->data["html_entity"];
    $this->iso_code              = $this->data["iso_code"];
    $this->iso_numeric           = $this->data["iso_numeric"];
    $this->name                  = $this->data["name"];
    $this->priority              = $this->data["priority"];
    $this->smallest_denomination = $this->data["smallest_denomination"];
    $this->subunit               = $this->data["subunit"];
    $this->subunit_to_unit       = $this->data["subunit_to_unit"];
    $this->symbol                = $this->data["symbol"];
    $this->symbol_first          = $this->data["symbol_first"];
    $this->thousands_separator   = $this->data["thousands_separator"];
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
    return round(log10($this->subunit_to_unit));
  }
}
