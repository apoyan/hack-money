<?hh // strict

namespace Money;
use Money\Currency\Currency as Currency;
use Money\Money\Formatter as Formatter;
use Money\Exception\CurrencyException as CurrencyException;
use Money\Exception\MoneyException as MoneyException;
use Money\Money\BigDecimal as BigDecimal;

class Money {
  private Formatter $formatter;
  private Currency $currency;
  private BigDecimal $_amount;
  const DEFAULT_CURRENCY = "USD";

  public function __construct(mixed $obj, mixed $currency, bool $from_cents = false): void {
    if($from_cents) {
      $this->currency = Money::to_currency($currency);
      $exponent = $this->currency->exponent();
      $this->_amount = new BigDecimal(bcdiv(strval($obj), $this->currency->getSubUnit(), $exponent));
    } else if($obj instanceof Money) {
      $this->_amount = $obj->amount();
      $this->currency = $obj->currency();
    } else {
      $this->_amount = new BigDecimal($obj);
      $this->currency = Money::to_currency($currency);

    }
    $this->formatter = new Formatter();
  }

  public static function fromCents(mixed $cents, mixed $currency): Money {
    return new self($cents, $currency, true);
  }

  public function amount(): BigDecimal {
    return $this->_amount;
  }

  public function to_cents(): int {
    $temp = new BigDecimal($this->getAmount(), $this->currency->exponent());
    return intval(preg_replace("/[^0-9-]/", "", $temp));
  }

  public function __toString(): string {
    return $this->getAmount();
  }

  public function getAmount(): string {
    return $this->_amount->getValue();
  }

  public function currency(): Currency {
    return $this->currency;
  }

  public function getCurrency(): string {
    return $this->currency->getCode();
  }

  public function format(?array<string, mixed> $rules = null): string {
    $rules = $rules ?? [];
    return $this->formatter->format($rules, $this);
  }

  public function equals(Money $other): bool {
    return $this->isSameCurrency($other) && $this->getAmount() === $other->getAmount();
  }

  public function add(Money $other): Money {
    $this->assertSameCurrency($other);
    return new self($this->_amount->add($other->getAmount()), $this->currency);
  }

  public function sub(Money $other): Money {
    $this->assertSameCurrency($other);
    return new self($this->_amount->sub($other->getAmount()), $this->currency);
  }

  public function mul(Money $other): Money {
    $this->assertSameCurrency($other);
    return new self($this->_amount->mul($other->getAmount()), $this->currency);
  }

  public function div(Money $other): Money {
    $this->assertSameCurrency($other);
    return new self($this->_amount->div($other->getAmount()), $this->currency);
  }

  public function isSameCurrency(Money $other): bool {
    return $this->currency->equals($other->currency);
  }

  private function assertSameCurrency(Money $other): void {
    if (!$this->isSameCurrency($other)) {
      throw new CurrencyException('Currencies must be identical');
    }
  }

  private static function to_currency(mixed $currency): Currency {
    if($currency instanceof Currency) {
      $temp_currency = $currency;
    } else if(is_string($currency)) {
      $temp_currency = new Currency($currency);
    } else {
      $temp_currency = new Currency(Money::DEFAULT_CURRENCY);
    }

    return $temp_currency;
  }
}
