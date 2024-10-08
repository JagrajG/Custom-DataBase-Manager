import sqlite3
import sys

class DatabaseManager:
    def __init__(self, dbName):
        self.connection = sqlite3.connect(dbName)
        self.cursor = self.connection.cursor()
        
        # Ensure the table is created when the class is initialized
        self.create_table("inventory")
    
    def create_table(self, tableName):
        create_table_sql = f"""CREATE TABLE IF NOT EXISTS {tableName}(
            BarCode INTEGER PRIMARY KEY AUTOINCREMENT,
            itemName TEXT NOT NULL,
            priceOfItem REAL NOT NULL,
            currentPromotions TEXT NOT NULL,
            stockCount INTEGER NOT NULL)"""
        self.cursor.execute(create_table_sql)
        self.connection.commit()
    
    def insert_item(self, itemName, priceOfItem, currentPromotions, stockCount, tableName):
        insert_sql = f"""INSERT INTO {tableName} (itemName, priceOfItem, currentPromotions, stockCount) VALUES(?,?,?,?);"""
        self.cursor.execute(insert_sql, (itemName, priceOfItem, currentPromotions, stockCount))
        self.connection.commit()

    def fetch_all_item(self, tableName):
        select_sql = f"SELECT * FROM {tableName}"
        self.cursor.execute(select_sql)
        items = self.cursor.fetchall()

        for item in items:
            print(f"ID: {item[0]:<5} | Item Name :{item[1]:<10} | Price ${item[2]:<6} | Promotion: {item[3]:<10} | Stock: {item[4]:<5}")
        return items
    
    def update(self, itemID, newPrice, tableName):
        update_sql = f"UPDATE {tableName} SET priceOfItem = ? WHERE BarCode = ?"
        self.cursor.execute(update_sql, (newPrice, itemID))
        self.connection.commit()
    
    def delete(self, itemID, tableName):
        delete_sql = f"DELETE FROM {tableName} WHERE BarCode = ?"
        self.cursor.execute(delete_sql, (itemID,))
        self.connection.commit()

    def close(self):
        self.connection.close()

if __name__ == "__main__":
    db_manager = DatabaseManager('inventory_management.db')
    
    if len(sys.argv) < 2:
        print("No command provided")
        sys.exit(1)

    command = sys.argv[1]
    table_name = "inventory"

    if command == "create_table":
        db_manager.create_table(table_name)
    elif command == "insert_item":
        item_name = sys.argv[2]
        price = float(sys.argv[3])
        promotions = sys.argv[4]
        stock_count = int(sys.argv[5])
        db_manager.insert_item(item_name, price, promotions, stock_count, table_name)
    elif command == "fetch_all":
        db_manager.fetch_all_item(table_name)
    elif command == "update_item":
        item_id = int(sys.argv[2])
        new_price = float(sys.argv[3])
        db_manager.update(item_id, new_price, table_name)
    elif command == "delete_item":
        item_id = int(sys.argv[2])
        db_manager.delete(item_id, table_name)
    
    db_manager.close()
