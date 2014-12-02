class CreateUsers < ActiveRecord::Migration
  def change
    create_table :users do |t|
      t.string :uuid
      t.integer :ipaddress
      t.integer :countrycode
      t.string :nickname
      t.integer :score
      t.text :results

      t.timestamps
    end
  end
end
