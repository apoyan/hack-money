<?hh // strict

namespace Money\Money;
use Money\Money;

class Formatter {
  private array<string, mixed> $rules = [];
  private bool $with_symbol = false;
  private bool $with_currency = false;
  private string $symbol_position = "before";
  private string $thousands_separator = ".";
  private string $decimal_mark = ".";
  private bool  $no_cents_if_whole = false;
  private int $exponent = 2;

  public function format(array<string, mixed> $rules, Money $money): string {
    $formatted = "";
    $this->rules = $rules;
    $amount = $money->getAmount();
    $this->exponent = $money->currency()->exponent();

    if($this->hasKeyValue("no_cents_if_whole", true) && $this->if_whole($amount)) {
      $amount = intval($amount);
      $this->exponent = 0;
    }

    if(array_key_exists("decimal_mark", $this->rules)) {
      $this->decimal_mark = (string) $this->rules['decimal_mark'];
    }

    if(array_key_exists("thousands_separator", $this->rules)) {
      $this->thousands_separator = (string) $this->rules['thousands_separator'];
    }
    $amount = number_format(floatval($money->getAmount()), $this->exponent, $this->decimal_mark, $this->thousands_separator);
    $amount = strval($amount);

    if($this->hasKeyValue("with_symbol", true)) {
      $formatted = $money->currency()->getSymbol();
    }

    if($this->hasKeyValue("symbol_position", "after")) {
      $formatted = $amount.$formatted;
    } else {
      $formatted = $formatted.$amount;
    }

    if($this->hasKeyValue("with_currency", true)) {
      $formatted = $formatted." ".$money->currency()->getCode();
    }

    return $formatted;
  }

  private function if_whole(string $amount): bool {
    $x = floatval($amount);
    $x -= floor($x);
    return $x == 0;
  }

  private function hasKeyValue(string $key, mixed $value):bool {
    return (array_key_exists($key, $this->rules) && $this->rules[$key] === $value);
  }
}
