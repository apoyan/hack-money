<?hh // strict

namespace Money\Money;
use Money\Money;

class Formatter {
  private array<string, mixed> $rules = [];
  private bool $sign = false;
  private bool $with_symbol = false;
  private bool $with_currency = false;
  private string $symbol_position = "before";
  private string $thousands_separator = ".";
  private string $decimal_mark = ".";
  private bool  $no_cents_if_whole = false;

  public function format(array<string, mixed> $rules, Money $money): string {
    $formatted = "";
    $amount = $money->getAmount();
    $this->rules = $rules;
    $sign = (substr($money->getAmount(), 0, 1) === '-') ? '-' : '';
    $thousands_separator = array_key_exists("thousands_separator", $this->rules) ?? $this->rules["thousands_separator"];
    $decimal_mark = array_key_exists("decimal_mark", $this->rules) ?? $this->rules["decimal_mark"];
    $amount = number_format(floatval($money->getAmount()), $money->currency()->exponent(), $decimal_mark, $thousands_separator);

    if($this->hasKeyValue("no_cents_if_whole", true)) {
      $amount = strval(intval($amount));
    } else {
      $amount = strval($amount);
    }

    if($this->hasKeyValue("with_symbol", true)) {
      $formatted = $money->currency()->getCode();
    }

    if($this->hasKeyValue("symbol_position", "after")) {
      $formatted = $formatted." ".$money->currency()->getCode();
    } else {
      $formatted = $money->currency()->getCode()." ".$formatted;
    }

    if($this->hasKeyValue("with_currency", true)) {
      $formatted = $formatted." ".$money->currency()->getName();
    }

    if($this->hasKeyValue("sign", true)) {
      $formatted = $sign.$formatted;
    }

    return $formatted;
  }

  private function hasKeyValue(string $key, mixed $value):bool {
    return (array_key_exists($key, $this->rules) && $this->rules[$key] === $value);
  }
}
