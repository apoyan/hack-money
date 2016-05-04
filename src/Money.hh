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

  public function __construct(mixed $obj, Currency $currency): void {
    if($obj instanceof Money) {
      $this->_amount = $obj->amount();
      $this->currency = $obj->currency();
    } else {
      $this->_amount = new BigDecimal($obj);
      $this->currency = $currency;
    }
    $this->formatter = new Formatter();
  }

  public function amount(): BigDecimal {
    return $this->_amount;
  }

  public function getAmount(): string {
    return $this->_amount->getValue();
  }

  public function currency(): Currency {
    return $this->currency;
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
}
