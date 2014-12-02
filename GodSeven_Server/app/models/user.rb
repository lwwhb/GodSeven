class User < ActiveRecord::Base
	validates :nickname, length: { maximum: 16 }
end
